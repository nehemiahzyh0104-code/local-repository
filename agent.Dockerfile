FROM node:24-bookworm

RUN corepack enable pnpm \
    && npm install -g @deepseek-ai/dsh @deepseek-harness-tui/dsh-tui \
    && npm cache clean --force

ENV HOME=/state \
    DSH_HOME=/state

CMD ["dsh", "web", "--no-open"]



# Creating a new sandbox

# docker build -t dsh - < agent.Dockerfile
# docker run -d --name dsh --mount type=bind,src=/persist/docker/dsh,dst=/state --mount type=bind,src=/mnt/inter/local-repository,dst=/workspace -w /workspace  -p 127.0.0.1:3080:3080 dsh sh -c 'set -- $(hostname -i); exec dsh web --no-open --host "$1" --public-url http://127.0.0.1:3080/ --trusted-host 127.0.0.1:3080'
# docker logs -f dsh