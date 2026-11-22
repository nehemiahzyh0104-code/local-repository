FROM node:24.22.3-bookworm

RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      bubblewrap ripgrep tmux less jq procps locales \
 && sed -i 's/^# *\(zh_SG.UTF-8 UTF-8\)/\1/' /etc/locale.gen \
 && locale-gen \
 && rm -rf /var/lib/apt/lists/*

RUN corepack enable pnpm \
 && npm install -g \
      "@deepseek-ai/dsh@0.2.2-rc.5" \
      "@deepseek-harness-tui/dsh-tui@0.20.2" \
 && npm cache clean --force

RUN curl -fsSL https://antigravity.google/cli/install.sh | bash \
 && mv /root/.local/bin/agy /usr/local/bin/agy \
 && agy --version

ENV HOME=/state \
    DSH_HOME=/state \
    CODEX_HOME=/state/.codex \
    TERM=xterm-256color \
    LANG=zh_SG.UTF-8 \
    LANGUAGE=zh_SG:zh \
    TZ=Asia/Singapore

CMD ["dsh", "web", "--no-open"]