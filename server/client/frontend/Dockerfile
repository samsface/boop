FROM node:latest

RUN apt-get update -y

WORKDIR /app

ADD . /app

RUN npm install && \
    npm run build && \
    npm install -g http-server &&  \
    mv dist ../dist && rm -rf * && mv /dist ./dist

EXPOSE 8080

CMD ["http-server", "-p", "8080", "dist"]
