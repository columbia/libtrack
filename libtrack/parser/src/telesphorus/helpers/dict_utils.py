"""
module documnetation
goes here
"""


def merge(dict_1, dict_2, func=lambda x, y: x + y):
    """doc"""
    res = dict_1.copy()  # "= dict(d1)" for lists of tuples
    for key, val in dict_2.iteritems():  # ".. in d2" for lists of tuple
        try:
            res[key] = func(res[key], val)
        except KeyError:
            res[key] = val
    return res
