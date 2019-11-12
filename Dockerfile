FROM lynix94/orca-build-base:1.0
MAINTAINER lynix94

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
	
