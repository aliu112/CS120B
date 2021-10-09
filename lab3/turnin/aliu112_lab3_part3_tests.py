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
# altered in between executions (unless preconditions are us

# Optionally you can add a set of "watch" variables these need to be global or static and may need
# to be scoped at the function level (for static variables) if there are naming conflicts. The 
# variables listed here will display everytime you hit (and stop at) a breakpoint
tests = [ {'description': 'PINA: 0x08,PINC =0x3C ',
    'steps': [ {'inputs': [('PINA',0x08)], 'iterations': 5 } ],
    'expected': [('PORTC', 0x3C)],
    },

    {'description': 'PINA: 0x04, PINC =0x70',
    'steps': [ {'inputs': [('PINA',0x04)], 'iterations': 5 } ],
    'expected': [('PORTC', 0x70)],
    },
    {'description': 'PINA: 0x0F => PORTc: 0x1F',
    'steps': [ {'inputs': [('PINA',0x0F)], 'iterations': 5 } ],
    'expected': [('PORTC',0x3F)],
    },
{'description': 'PINA: 0x5 => PORTC: 0x38',
    'steps': [ {'inputs': [('PINA',0x05)], 'iterations': 5 } ],
    'expected': [('PORTC',0x38)],
    },
{'description': 'PINA: 0x38 => PORTC: 0xBC',
    'steps': [ {'inputs': [('PINA',0x38)], 'iterations': 5 } ],
    'expected': [('PORTC',0xBC)],
    },
{'description': 'PINA: 0x78 => PORTB: 0x3C',
    'steps': [ {'inputs': [('PINA',0x78)], 'iterations': 5 } ],
    'expected': [('PORTC',0x3C)],
    },

    ]
