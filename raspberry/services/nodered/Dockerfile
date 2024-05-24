# reference argument - omitted defaults to latest
ARG DOCKERHUB_TAG=latest

# Download base image
FROM nodered/node-red:${DOCKERHUB_TAG}

# reference argument - omitted defaults to null
ARG EXTRA_PACKAGES
ENV EXTRA_PACKAGES=${EXTRA_PACKAGES}

# default user is node-red - need to be root to install packages
USER root

# install packages
RUN apk update && apk add --no-cache eudev-dev ${EXTRA_PACKAGES}

# switch back to default user
USER node-red

# variable not needed inside running container
ENV EXTRA_PACKAGES=

# add-on nodes follow

RUN cd /usr/src/node-red && npm install --save  node-red-configurable-ping
RUN cd /usr/src/node-red && npm install --save  node-red-contrib-boolean-logic
RUN cd /usr/src/node-red && npm install --save  node-red-contrib-influxdb
RUN cd /usr/src/node-red && npm install --save  node-red-dashboard
RUN cd /usr/src/node-red && npm install --save  node-red-node-pi-gpiod
RUN cd /usr/src/node-red && npm install --save  node-red-node-rbe

