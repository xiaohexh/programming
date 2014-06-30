#!/usr/bin/python

import re

m = re.search('[0-9]', 'ab4ce5')
print m.group(0)
