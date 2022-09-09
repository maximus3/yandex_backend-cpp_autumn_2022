FROM conanio/gcc7:latest

COPY ./src app
# Specify the working directory
WORKDIR app
EXPOSE 8000
USER root
RUN chmod 777 -R /home/conan/app
USER conan
RUN mkdir build
RUN conan install . -s compiler.libcxx=libstdc++11 -if build --build missing
RUN cd build && cmake .. && cmake --build .
CMD ["build/bin/disk_rest_api"]