FROM debian:bookworm-slim AS builder

RUN apt-get update \
	&& apt-get install --no-install-recommends -y \
		build-essential \
		libreadline-dev \
	&& rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN make


FROM debian:bookworm-slim

RUN apt-get update \
	&& apt-get install --no-install-recommends -y \
		libreadline8 \
		ttyd \
		coreutils \
		grep \
		sed \
	&& rm -rf /var/lib/apt/lists/* \
	&& useradd --create-home --shell /bin/bash demo

WORKDIR /app

COPY --from=builder /app/minishell ./minishell

RUN chown -R demo:demo /app \
	&& chmod +x /app/minishell

USER demo

ENV HOME=/home/demo
ENV TERM=xterm-256color

EXPOSE 7681

CMD ["sh", "-c", "exec ttyd --writable --max-clients 1 --interface 0.0.0.0 --port ${PORT:-7681} ./minishell"]
