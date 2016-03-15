#!/usr/bin/env python

from setuptools import setup

setup(name='telesphorus',
      version='0.1',
      description='Telesphorus',
      author='Vaggelis Atlidakis',
      author_email='vatlidak@cs.columbia.edu',
      package_dir={'': 'src'},
      packages=['telesphorus', 'telesphorus.helpers'],
      test_suite="tests",
      scripts=['bin/telesphorus',
        ],
    )
