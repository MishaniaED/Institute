FROM python:3.11

ENV PYTHONUNBUFFERED 1

ADD .. /app

# Set the working directory
WORKDIR /app

# Install the dependencies
RUN pip install --upgrade pip
RUN pip install -r requirements.txt

# Expose port 8000
EXPOSE 8000
