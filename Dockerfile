# syntax=docker/dockerfile:1

# Build Minishell in a disposable stage.
FROM debian:bookworm-slim AS minishell-builder

RUN apt-get update \
	&& apt-get install --no-install-recommends -y \
		build-essential \
		libreadline-dev \
	&& rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY Makefile minishell.h *.c ./
COPY 42_libft ./42_libft
COPY parsing ./parsing

RUN make -j"$(nproc)" \
	&& strip /app/minishell


# Obtain ttyd from its official image. Keep this version explicit so rebuilds
# do not unexpectedly change the web terminal implementation.
FROM tsl0922/ttyd:1.7.7 AS ttyd-source


# Runtime image
FROM ubuntu:24.04

RUN apt-get update \
	&& apt-get install --no-install-recommends -y \
		libreadline8t64 \
		bash \
		coreutils \
		grep \
		sed \
		tini \
	&& rm -rf /var/lib/apt/lists/* \
	&& useradd --create-home --shell /bin/bash demo

WORKDIR /app

COPY --from=minishell-builder /app/minishell /app/minishell
COPY --from=ttyd-source /usr/bin/ttyd /usr/bin/ttyd

RUN chown -R demo:demo /app /home/demo

USER demo

ENV HOME=/home/demo \
	TERM=xterm-256color \
	PORT=7681

EXPOSE 7681

ENTRYPOINT ["/usr/bin/tini", "--"]

CMD ["sh", "-c", "exec ttyd -W -i 0.0.0.0 -p ${PORT:-7681} /app/minishell"]
