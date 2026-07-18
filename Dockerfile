# Build Minishell
FROM debian:bookworm-slim AS minishell-builder

RUN apt-get update \
	&& apt-get install --no-install-recommends -y \
		build-essential \
		libreadline-dev \
	&& rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN make


# Obtain ttyd from its official image
FROM tsl0922/ttyd:latest AS ttyd-source


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

RUN chmod +x /app/minishell /usr/bin/ttyd \
	&& chown -R demo:demo /app /home/demo

USER demo

ENV HOME=/home/demo
ENV TERM=xterm-256color

EXPOSE 7681

ENTRYPOINT ["/usr/bin/tini", "--"]

CMD ["sh", "-c", "exec ttyd -W -m 1 -i 0.0.0.0 -p ${PORT:-7681} /app/minishell"]