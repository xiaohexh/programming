#!/usr/bin/python
# Filename: replace_str.py

import string

originStr = '92.82.22.46 - - [2013-07-03T00:29:40-05:00] "GET /images/mask_bg.png HTTP/1.1" 200 195'

#destStr = '92.82.22.46 - - "2013-07-03 00:29:40-05:00" "GET /images/mask_bg.png HTTP/1.1" 200 195'

# replace '[]' with '""'
print originStr
table = string.maketrans('[]', '""')
mid = originStr.translate(table)
print mid

# replace '2013-07-03T00:29:40-05:00' with '2013-07-03 00:29:40-05:00'
last = originStr.translate(table).replace('T', ' ', 1)
print last
