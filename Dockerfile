FROM ubuntu:18.04
MAINTAINER lynix94

RUN apt -y update; \
	apt install -y git; \
	apt install -y gcc g++ make autoconf automake git; \
	apt install -y iputils-ping net-tools telnet vim; \
	apt install -y libtool flex bison \
		libboost-all-dev libreadline-dev libgmp-dev \
		libgtk2.0-dev libsqlite3-dev libleveldb-dev \
		libcanberra-gtk-module libssl-dev

RUN set -ex; \
	git clone https://github.com/lynix94/orca-lang; \
	cd /orca-lang; \
	./autogen.sh; \
	./configure --prefix=/orca; \
	make; \
	make install

ENV PATH /orca/bin:$PATH
ENV LD_LIBRARY_PATH .:$LD_LIBRARY_PATH
ENV ORCA_PATH /orca/lib/orca
ENV ORCA_HOME /orca
	
