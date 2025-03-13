FROM nginx:latest

USER root

WORKDIR /home/

RUN apt-get update && apt-get install -y --no-install-recommends \
    libc6-dev \
    libfcgi-dev \
    gcc \
    spawn-fcgi \
    && rm -rf /var/lib/apt/lists/*

COPY nginx.conf /etc/nginx/nginx.conf
COPY start.sh .

RUN chown -R nginx:nginx /home/; \
    chown -R nginx:nginx /etc/nginx/nginx.conf; \
    chown -R nginx:nginx /var/cache/nginx; \
    touch /var/run/nginx.pid; \
    chown -R nginx:nginx /var/run/nginx.pid; \
    chmod u-s /usr/bin/su; \
    chmod u-s /usr/bin/mount; \
    chmod u-s /usr/bin/gpasswd; \
    chmod g-s /usr/bin/chage; \
    chmod g-s /usr/sbin/unix_chkpwd; \
    chmod g-s /usr/bin/expiry; \
    chmod u-s /usr/bin/chfn; \
    chmod u-s /usr/bin/chsh; \
    chmod u-s /usr/bin/passwd; \
    chmod u-s /usr/bin/newgrp; \
    chmod u-s /usr/bin/umount; \
    chmod g-s /usr/bin/wall;

USER nginx
ENTRYPOINT ["sh", "./start.sh"]

HEALTHCHECK NONE