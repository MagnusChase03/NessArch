FROM docker.io/gcc

RUN mkdir code
WORKDIR code

COPY . .
RUN make test_build

CMD make test
