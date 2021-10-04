# Array of tests to run (in order)
# Each test contains
#   description - 
#   steps - A list of steps to perform, each step can have
#       inputs - A list of tuples for the inputs to apply at that step
#       *time - The time (in ms) to wait before continuing to the next step 
#           and before checking expected values for this step. The time should be a multiple of
#           the period of the system
#       *iterations - The number of clock ticks to wait (periods)
#       expected - The expected value at the end of this step (after the "time" has elapsed.) 
#           If this value is incorrect the test will fail early before completing.
#       * only one of these should be used
#   expected - The expected output (as a list of tuples) at the end of this test
# An example set of tests is shown below. It is important to note that these tests are not "unit tests" in 
# that they are not ran in isolation but in the order shown and the state of the device is not reset or 
# altered in between executions (unless preconditions are used).
tests = [ {'description': 'PINA: 0xA0, PINB = 0x40, PINC =0x00 => PORTD = 0xE3 ',
    'steps': [ {'inputs': [('PINA',0xA0),('PINB',0x40),('PINC',0x00)], 'iterations': 5 } ],
    'expected': [('PORTD', 0xE3)],
    },

    {'description': 'PINA: 0x00, PINB = 0xA0, PINC =0x60 => PORTD = 0x03 ',
    'steps': [ {'inputs': [('PINA',0x00),('PINB',0xA0),('PINC',0x60)], 'iterations': 5 } ],
    'expected': [('PORTD', 0x03)],
    },

    {'description': 'PINA: 0x60, PINB = 0xA0, PINC =0x60 => PORTD = 0x61 ',
    'steps': [ {'inputs': [('PINA',0x60),('PINB',0xA0),('PINC',0x60)], 'iterations': 5 } ],
    'expected': [('PORTD', 0x61)],
    },

    {'description': 'PINA: 0x03, PINB = 0xA0, PINC =0x03 => PORTD = 0xA5 ',
    'steps': [ {'inputs': [('PINA',0x03),('PINB',0xA0),('PINC',0x03)], 'iterations': 5 } ],
    'expected': [('PORTD', 0xA5)],
    },

    {'description': 'PINA: 0x40, PINB = 0x40, PINC =0x40 => PORTD = 0x31 ',
    'steps': [ {'inputs': [('PINA',0x40),('PINB',0x40),('PINC',0x40)], 'iterations': 5 } ],
    'expected': [('PORTD', 0x31)],
    },

    {'description': 'PINA: 0x00, PINB = 0x23, PINC =0x55 => PORTD = 0x1E ',
    'steps': [ {'inputs': [('PINA',0x00),('PINB',0x23),('PINC',0x55)], 'iterations': 5 } ],
    'expected': [('PORTD', 0x1E)],
    },
{'description': 'PINA: 0x00, PINB = 0x38, PINC =0x55 => PORTD = 0x23 ',
    'steps': [ {'inputs': [('PINA',0x00),('PINB',0x38),('PINC',0x55)], 'iterations': 5 } ],
    'expected': [('PORTD', 0x23)],
    },









    ]
#watch = ['PORTB']
