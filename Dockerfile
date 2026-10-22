FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN mkdir build && cd build && cmake .. && make

CMD ["sh", "-c", "cd build && ctest --output-on-failure && ./main_app"]
