FROM node:24.22.3-bookworm

RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      bubblewrap ripgrep tmux less jq procps \
 && rm -rf /var/lib/apt/lists/*

RUN corepack enable pnpm \
 && npm install -g \
      "@deepseek-ai/dsh@0.2.2-rc.1" \
      "@deepseek-harness-tui/dsh-tui@0.20.1" \
      "@openai/codex@0.168.0" \
 && npm cache clean --force

ENV HOME=/state \
    DSH_HOME=/state \
    CODEX_HOME=/state/.codex \
    LANG=C.UTF-8

CMD ["dsh", "web", "--no-open"]