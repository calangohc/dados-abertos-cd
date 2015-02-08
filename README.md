# Dados Abertos da Câmara dos Deputados
=======================================

Soluções para acesso, exploração e consumo dos Dados Abertos disponibilizados pela Câmara dos Deputados do Brasil

### Python

Para montar o ambiente de desenvolvimento Python necessário para utilizar este código no Linux, siga as seguintes orientações:

1) Obtenha a versão atual do virtualenv:
https://pypi.python.org/pypi/virtualenv#downloads
tar xvf virtualenv*

2) Crie um ambiente inicial para ele:
python virtualenv.py ~/py-env0 

3) Instale o virtualenv neste ambiente:
~/py-env0/bin/pip virtualenv*.tar.gz

4) Crie e ative o ambiente do projeto:
~/py-env0/bin/virtualenv pasta_do_projeto/env
pasta_do_projeto/env/bin/activate 

5) Instale o pacote python-dev
sudo apt-get install python-dev

6) Instale os requisitos do projeto:
pip install -r requirements.txt

Referência:

http://stackoverflow.com/questions/4324558/whats-the-proper-way-to-install-pip-virtualenv-and-distribute-for-python
