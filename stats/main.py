from os import system
from timeit import time

def getTime(cmd):
  start_time = time.time()
  system(cmd)
  end_time = time.time()
  elapsed = end_time - start_time
  return elapsed

def runTest(pattern_file, text_file, max_error, algorithm):
  return getTime('./bin/pmt -p {} {} -c -e {} -a {} > /dev/null'.format(
      pattern_file, text_file, max_error, algorithm))

def main():
  algos = [
    ('naive',   False),
    ('kmp',     False),
    ('aho',     False),
    ('so',      False),
    ('bm',      False),
    ('sellers', True),
    ('ukkonen', True)
  ]
  tests = [
    ('test/blue.txt', 'test/english', 0),
    ('test/blue.txt', 'test/english', 1),
    ('test/blue.txt', 'test/english', 2),
    ('test/marshmallow.txt', 'test/english', 0),
    ('test/marshmallow.txt', 'test/english', 1),
    ('test/marshmallow.txt', 'test/english', 2),
  ]

  for pat, txt, err in tests:
    for alg, app in algos:
      if not app and err > 0: continue
      time = runTest(pat, txt, err, alg)
      result = (pat, txt, err, alg, time)
      print('{:30} {:30} {:5} {:10} {:5.4f}'.format(pat, txt, err, alg, time))

if __name__ == '__main__':
  main()
