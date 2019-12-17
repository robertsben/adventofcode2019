FROM gcc
WORKDIR /usr/src
COPY input.txt .
COPY test_1.txt .
COPY test_2.txt .
COPY test_3.txt .
COPY src .
RUN gcc -o solution -Ofast solution.c
CMD ["./solution"]

