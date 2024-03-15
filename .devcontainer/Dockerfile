FROM rockylinux:9.3

RUN export DEBIAN_FRONTEND=noninteractive

COPY welcome.txt /tmp/scripts/

RUN dnf -y update && \
    dnf -y install man-db && \
    dnf -y install vim && \
    dnf clean all

ENV USERNAME='LENS'
ENV USER_UID=1000
ENV USER_GID=1000

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid ${USER_UID} --gid ${USER_GID} -m ${USERNAME} \
    && dnf install -y sudo \
    && echo ${USERNAME} ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/${USERNAME} \
    && chmod 0440 /etc/sudoers.d/${USERNAME} \
    && dnf install -y \
        systemd \
        passwd \
    && mkdir /opt/projects \
    && chown -R ${USERNAME}.${USERNAME} /opt/projects


RUN dnf install -y \
    gcc \
    g++ \
    cmake \
    make \
    unzip \
    git \
    wget \
    perl-CPAN \
    python3.11 \
    python3.11-pip \
    dos2unix \
    readline \
    readline-devel \
    libnsl \
    libcurl \
    libcurl-devel --allowerasing --nobest && \
    dnf clean all

RUN dnf install -y --allowerasing \
    git \
    libcurl && \
    dnf clean all

RUN dnf autoremove -y && dnf clean all \
    && mkdir -p "/usr/local/etc/vscode-dev-containers/" \
    && mv -f /tmp/scripts/welcome.txt /usr/local/etc/vscode-dev-containers/

ENV SHELL=/bin/bash \
    DOCKER_BUILDKIT=1


RUN wget https://cmake.org/files/v3.25/cmake-3.25.3.tar.gz \
    && tar xzf cmake-3.25.3.tar.gz \
    && cd cmake-3.25.3 \
    && wget  https://rocky-linux-asia-south2.production.gcp.mirrors.ctrliq.cloud/pub/rocky//9.3/AppStream/x86_64/os/Packages/g/gcc-c%2b%2b-11.4.1-2.1.el9.x86_64.rpm \
    && dnf install -y libstdc++-devel-11.4.1-2.1.el9 openssl-devel

RUN cd cmake-3.25.3 && ./configure --prefix=/opt/cmake \
    && make \
    && make install

RUN { dnf install -y epel-release && dnf makecache; } &>> /var/log/install-gitlab.log

RUN curl -s https://packagecloud.io/install/repositories/rabbitmq/rabbitmq-server/script.rpm.sh | bash && \
    curl -1sLf 'https://dl.cloudsmith.io/public/rabbitmq/rabbitmq-erlang/setup.rpm.sh' | bash && \
    dnf makecache && \
    dnf -y install rabbitmq-server

RUN dnf install -y dnf-plugins-core

RUN sudo -S dnf update -y

RUN  sudo -S dnf install -y unzip

RUN sudo -S mkdir /opt/awscli && \
    sudo -S chmod 777 -R /opt/awscli

RUN sudo -S dnf install -y python3-pip && \
    pip3 install awscli

RUN dnf clean all && rm -rf /tmp/scripts

VOLUME [ "/var/lib/docker" ]

ENTRYPOINT [ "/usr/local/share/docker-init.sh", "/usr/local/share/ssh-init.sh"]
CMD [ "sleep", "infinity" ]

