FROM ubuntu

RUN apt-get update && apt-get install -y gcc make valgrind vim check

COPY . /code

WORKDIR /code

CMD /bin/bash
