FROM conanio/gcc9:latest

COPY ./src app
# Specify the working directory
WORKDIR app
EXPOSE 80
USER root
RUN chmod 777 -R /home/conan/app
USER conan
RUN mkdir .build
RUN cd .build && conan install .. -s compiler.libcxx=libstdc++11 --build missing
RUN cd .build && cmake .. && cmake --build .
CMD [".build/bin/disk_rest_api"]