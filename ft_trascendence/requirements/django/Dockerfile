FROM python:3.9

WORKDIR /var/www/html/back

COPY utils/requirements.txt /tmp/requirements.txt
RUN pip install --no-cache-dir -r /tmp/requirements.txt

COPY utils/run.sh /tmp/run.sh

RUN chmod +x /tmp/run.sh
ENTRYPOINT [ "/tmp/run.sh" ]
