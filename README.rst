volsync
=======

Synchronize the master volume between a Linux computer and a motor fader via
nRF24L01 transceiver.


Wiring
------

The code is written for the *Atmel ATtiny44a* microcontroller. The following
wiring is being used:

.. image:: https://raw.githubusercontent.com/dbrgn/volsync/master/t44a.png
    :alt: Microcontroller pins

**PSU**

:VCC: 5V
:GND: Ground

**Transceiver (nRF24L01)**

:VCC: VCC
:GND: GND
:PB0: CE
:PB1: CSN
:PA6: MOSI
:PA5: MISO
:PA4: SCL
:PA3: IRQ

**Potentiometer**

:PA1: ADC1 (pot)
:PA0: AREF (pot)


License
-------

MIT License.
