FROM alpine:3.8

ARG USER_ID=1000
ARG GROUP_ID=1000

RUN	apk --no-cache add g++ make \
	&& addgroup -g $GROUP_ID -S make-group \
	&& adduser -u $USER_ID -D -S -G make-group -s /bin/sh make-user

VOLUME /app

WORKDIR /app

USER make-user:make-group

ENTRYPOINT ["make"]
