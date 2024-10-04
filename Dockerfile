FROM gocv/opencv

RUN apt-get update && apt-get install -y sudo build-essential git cmake curl unzip tar curl zip && rm -rf /var/lib/apt/lists/*
WORKDIR /home
RUN git clone https://github.com/Microsoft/vcpkg.git
WORKDIR /home/vcpkg
RUN ./bootstrap-vcpkg.sh
# Optionally, integrate vcpkg with CMake (for easier use)
RUN /home/vcpkg/vcpkg integrate install

# Add vcpkg to the PATH so you can use it easily
ENV PATH="/home/vcpkg:${PATH}"

# Set the working directory inside the container
WORKDIR /app

RUN vcpkg install nlohmann-json

# Copy your C++ project into the container
COPY . .

# Update package lists and install the latest CMake
RUN apt-get update && apt-get install -y cmake

# Build the project
RUN mkdir build && cd build && \
    cmake ../  && \
    make

# Set the command to run your application
CMD ["./build/main"]
