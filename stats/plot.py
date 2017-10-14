import numpy as np
import matplotlib.pyplot as plt

algos = [
  ('naive',   False),
  ('kmp',     False),
  ('aho',     False),
  ('so',      False),
  ('bm',      False),
  ('sellers', True),
  ('ukkonen', True)
]

results_per_alg = {}
with open('stats/results.txt') as results:
  for line in results:
    if not line.strip(): continue
    pat, txt, err, alg, tim = line.split()
    # print(tim);
    test = (pat, txt, err);
    
    if alg not in results_per_alg:
      results_per_alg[alg] = []
    results_per_alg[alg].append(tim)

for alg in results_per_alg:
  results = results_per_alg[alg]
  plt.plot(results)
plt.show()

