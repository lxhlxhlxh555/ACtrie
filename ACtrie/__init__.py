import _ACtrie

from itertools import groupby
from intervaltree import IntervalTree

class ACtrie(object):
    def __init__(self):
        self.ac = _ACtrie.new()
        self.is_remove_overlaps = False

    def insert(self, string):
        _ACtrie.insert(self.ac, string)

    def match_all(self, string):
        result = _ACtrie.match_all(self.ac, string)

        if self.is_remove_overlaps:
            tree = IntervalTree()
            new_result = []
            for beg, word in result:
                end = beg + len(word)
                if not tree.overlaps(beg, end):
                    tree[beg:end] = True
                    new_result.append((beg,word))
            del tree
            result = new_result
        return result

    def case_insensitive(self):
        return _ACtrie.case_insensitive(self.ac)

    def remove_overlaps(self):
        # return None
        self.is_remove_overlaps = True
        return None

    def only_whole_words(self):
        return _ACtrie.only_whole_words(self.ac)
