Show Laser Documentation
=============================================================================

# The galvonometers

    A galvanometer is a instrument that move around an axe, proportionally to
    the amount of current which he is powered.
    A mirror is mount on a galvanometer and reflect a laser ray. With a second
    mirror on a second galvanometer which axe is perpendicular to the first
    one, that reflect the ray reflected by the first mirror, you have a
    installation where you can point a laser according to two axes (X and Y).

    A galvanometer is brushless and can move really fast. This is why it is
    used in Laser Shows.
    The control of a galvanometer is purely analogic and you need and hardware
    analogic PID to have the best performances, this is a tricky task so we
    will directly get a galvanometer scanner from jmlaser (www.jmlaser.com)

    The scanner takes in entry a voltage from -10V up to +10V and control the
    galvanometer. We will use the DAC from our processor (0, 3.3V), use an
    amplifier (-10V, +10v) and give this voltage to the scanner, that
    transform it into an angle of a mirror.

# Persistence of vision

    The human eye has 250ms persistence on the retinal. It means that a light
    stays visible by a human eye for 1/25s after disapearing. It means that if
    of make a light blink faster than 25Hz the eye can see how many time the
    light stays on by detecting the intensity of the light, but the eye does
    not detect the moment your light is off.

    This phenomemun is really convenient for many applications, PWM,
    projection of an anologic movie in a theater, and so on.
    On a lazer show, the ray moves really fast so you do not see a ray but
    forms.

    This is why we need to move really fast to obtain this effect, and this is
    why we use galvanometers.

# Naked eye

    The limit of our eyes

    Angular resolution 0.007° (4 arcminutes)

# Laser show theory
## Frame rate
    Just like a movie that display 24 frames by seconds (if you are too young
    and know only the HD movie digitalised at 60 frames by seconds, it used to
    be 24). We will display consecutives frames, the rate is fixed at
    (TODO 24 min) frames by seconds.

    The main problem is a mechanical problem, we need to have the time to scan
    the complete form whitin the frame time associated to the rate (1/rate).
    In the case of a rate of 24 frames per seconds. The frame time is
    approximately 42ms.

## Display angles
    To decide what rate we will use, we need to define the show display angles

    First of all the angle precision:
       start at the source, the STM32F4 Digital-to-Analog Converter range and
       precision.



