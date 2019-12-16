FROM gcc
WORKDIR /usr/src
COPY input.txt .
COPY src .
RUN gcc -o solution -Ofast solution.c
CMD ["./solution"]

