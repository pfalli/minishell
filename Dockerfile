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
	&& rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=builder /app/minishell ./minishell

ENTRYPOINT ["./minishell"]
