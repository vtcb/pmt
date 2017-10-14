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

def runPattern(pattern, text_file, max_error, algorithm):
  return getTime('./bin/pmt "{}" {} -c -e {} -a {} > /dev/null'.format(
      pattern, text_file, max_error, algorithm))

patterns = [
  'blue',
  'marshmallow',
  'church',
  'hello',
  'functioning',
  'door',
  'Revolutionary',
  'thing',
  'I',
  'antiquarians',
  'maintain',
  'exaggeration',
  'specially',
  'splendid',
  'programming',
  'tinker',
  'thinking',
  'wonderful',
  'thunderstruck',
  'engagement',
  'children',
  
  'from the Russian proletariat',
  'Judaism is founded',
  'O King of the Age',
  'And I tried it',
  'directly between the eyes',
  'four quarters of the globe',
  'The journey to Chester',
  'gave her children',
  'pen pineapple apple pen',
  'I haven\'t got',
  'light and darkness'
]

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
    ('test/church.txt', 'test/english', 0),
    ('test/church.txt', 'test/english', 1),
    ('test/church.txt', 'test/english', 2),
    ('test/A.txt', 'test/dna', 0),
    ('test/A50.txt', 'test/dna', 0),
    ('test/A50.txt', 'test/dna', 1),
    ('test/A50.txt', 'test/dna', 2),
  ]

  system('make')
  for pat, txt, err in tests:
    for alg, app in algos:
      if not app and err > 0: continue
      time = runTest(pat, txt, err, alg)
      result = (pat, txt, err, alg, time)
      print('{:30} {:30} {:5} {:10} {:5.4f}'.format(pat, txt, err, alg, time))

if __name__ == '__main__':
  main()
