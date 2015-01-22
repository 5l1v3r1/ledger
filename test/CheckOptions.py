#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import print_function

import sys
import re
import os
import argparse

from os.path import *
from subprocess import Popen, PIPE

class CheckOptions (object):
  def __init__(self, args):
    self.option_pattern = None
    self.source_file = None
    self.sep = "\n  --"

    self.ledger     = os.path.abspath(args.ledger)
    self.source     = os.path.abspath(args.source)

    self.missing_baseline_tests = set()
    self.missing_options = set()
    self.unknown_options = set()

    self.untested_options = [
        'anon',
        'args-only',
        'cache',
        'debug',
        'download',
        'file',
        'force-color',
        'force-pager',
        'full-help',
        'help',
        'help-calc',
        'help-comm',
        'help-disp',
        'import',
        'init-file',
        'no-color',
        'options',
        'price-db',
        'price-exp',
        'revalued-total',
        'script',
        'seed',
        'trace',
        'verbose',
        'verify',
        'version'
    ]

    self.known_alternates = [
        'cost',
        'first',
        'import',
        'last',
        'leeway',
        'period-sort'
    ]

  def find_options(self, filename):
    regex = re.compile(self.option_pattern)
    return {match.group(1) for match in {regex.match(line) for line in open(filename)} if match}

  def ledger_options(self):
    pipe   = Popen('%s --debug option.names parse true' %
        self.ledger, shell=True, stdout=PIPE, stderr=PIPE)
    regex = re.compile('\[DEBUG\]\s+Option:\s+(.*?)_?$')
    ledger_options = {match.group(1).replace('_', '-') for match in {regex.search(line.decode()) for line in pipe.stderr} if match}
    return ledger_options

  def main(self):
    options = self.find_options(self.source_file)

    for option in self.ledger_options():
      if option not in options:
          self.missing_options.add(option)
      else:
          options.remove(option)

    self.unknown_options = {option for option in options if option not in self.known_alternates}

    if len(self.missing_options):
      print("Missing %s entries for:%s%s\n" % (self.source_type, self.sep, self.sep.join(sorted(list(self.missing_options)))))
    if len(self.unknown_options):
      print("%s entry for unknown options:%s%s" % (self.source_type, self.sep, self.sep.join(sorted(list(self.unknown_options)))))

    errors = len(self.missing_options) + len(self.unknown_options)
    return errors
