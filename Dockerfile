# Writen by wicked1133
# https://github.com/gabeluci/ARInside/issues/2#issuecomment-2013951363

# Use an official C++ development image as the base image
ARG GCC_VERSION=13.2.0
FROM --platform=linux/amd64 gcc:${GCC_VERSION}

# Set version
ARG ARINSIDE_VERSION=3.1.5
ARG ARINSIDE_ARCH=${ARINSIDE_VERSION}-linux_x64

# Set the working directory
WORKDIR /app

# Download and unzip file
RUN wget https://github.com/gabeluci/ARInside/releases/download/v${ARINSIDE_VERSION}/arinside-${ARINSIDE_ARCH}.zip \
  && unzip *${ARINSIDE_ARCH}.zip \
  && rm -f *${ARINSIDE_ARCH}.zip

# Install ARinside
RUN chmod +x arinside* \
  && cp arinside /usr/bin/ \
  && mv lib* /usr/lib/

# Copy Settings.ini from Host
COPY settings.ini .

# Run ARinside with settings
CMD ["arinside", "-i", "settings.ini"]
