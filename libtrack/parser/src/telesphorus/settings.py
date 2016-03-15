"""
docstring of module
goes here
"""

from configobj import ConfigObj, flatten_errors
from configobj import ConfigObjError
from validate import Validator

from errors import TelesphorusConfigError
from configfile import CONFIG_GRAMMAR


class Settings():
    def __init__(self):
        pass

    def parse_config(self, config_file_path):
        try:
            config = ConfigObj(infile=config_file_path,
                               configspec=CONFIG_GRAMMAR.split("\n"),
                               file_error=True)
        except (ConfigObjError, IOError), error:
            raise TelesphorusConfigError("Config file parsing failed (%s)"
                                         % error)
        validator = Validator()
        results = config.validate(validator)

        print "Validating configuration file '%s'" % config_file_path
        if not results:
            for section_list, key, _ in flatten_errors(config, results):
                section_string = '.'.join(section_list)
                if key is not None:
                    raise TelesphorusConfigError("Missing key %s section %s"
                                                 % (key, section_string))
                else:
                    raise TelesphorusConfigError("Section '%s' is missing"
                                                 % section_string)

        self.DEGREE_IN = config["main"]["degree_in"]
        self.FULL_PATH = config["main"]["full_path"]
        self.LIB_CALL = config["main"]["lib_call"]
        self.POSIX_CALL = config["main"]["posix_call"]
        self.TIMING_POSIX = config["main"]["timing_posix"]
        self.STACK_DEPTH = config["main"]["stack_depth"]
        self.LIB = config["main"]["lib"]
        self.HIDDEN_ABSTR = config["main"]["hidden_abstr"]
        self.OBSOLETE_ABSTR = config["main"]["obsolete_abstr"]
        self.MISSING_ABSTR = config["main"]["missing_abstr"]
        self.CIRCULAR_ABSTR = config["main"]["circular_abstr"]
        self.OBSCURITY_RATIO = config["main"]["obscurity_ratio"]

        self.FULL_PATH_THREASHOLD = config["main"]["full_path_threashold"]
        self.LIB_THREASHOLD = config["main"]["lib_threashold"]
        self.LIB_CALL_THREASHOLD = config["main"]["lib_call_threashold"]
        self.POSIX_CALL_THREASHOLD = config["main"]["posix_call_threashold"]
        self.HIDDEN_ABSTR_THREASHOLD = config["main"]["hidden_abstr_threashold"]
        self.OBSOLETE_ABSTR_THREASHOLD = config["main"]["obsolete_abstr_threashold"]
        self.MISSING_ABSTR_SAMPLES = config["main"]["missing_abstr_samples"]
        self.MISSING_ABSTR_MAX_WINDOW_SIZE = config["main"]["missing_abstr_max_window_size"]
        self.CIRCULAR_ABSTR_SAMPLES = config["main"]["circular_abstr_samples"]
        self.OBSCURITY_SAMPLES = config["main"]["obscurity_samples"]
