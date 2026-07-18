FROM debian:bookworm-slim AS builder

RUN apt-get update \
	&& apt-get install --no-install-recommends -y \
		build-essential \
		libreadline-dev \
	&& rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .
RUN make


FROM tsl0922/ttyd:latest

USER root

RUN apk add --no-cache \
	readline \
	bash \
	coreutils \
	grep \
	sed \
	&& adduser -D -s /bin/bash demo

WORKDIR /app

COPY --from=builder /app/minishell ./minishell

RUN chown -R demo:demo /app \
	&& chmod +x /app/minishell

USER demo

ENV HOME=/home/demo
ENV TERM=xterm-256color

EXPOSE 7681

CMD ["sh", "-c", "exec ttyd --writable --max-clients 1 --interface 0.0.0.0 --port ${PORT:-7681} ./minishell"]