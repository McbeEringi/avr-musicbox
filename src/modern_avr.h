#ifndef MODERN_AVR_H
#define MODERN_AVR_H

#if (
	defined(__AVR_ATtiny202__)||
	defined(__AVR_ATtiny402__)||
	defined(__AVR_ATtiny212__)||
	defined(__AVR_ATtiny412__)
)
	#define TINYAVR
	#define TINYAVR_8PIN
#endif

#if (
	defined(__AVR_ATtiny204__)||
	defined(__AVR_ATtiny404__)||
	defined(__AVR_ATtiny804__)||
	defined(__AVR_ATtiny1604__)||

	defined(__AVR_ATtiny214__)||
	defined(__AVR_ATtiny414__)||
	defined(__AVR_ATtiny814__)||
	defined(__AVR_ATtiny1614__)||

	defined(__AVR_ATtiny424__)||
	defined(__AVR_ATtiny824__)||
	defined(__AVR_ATtiny1624__)||
	defined(__AVR_ATtiny3224__)
)
	#define TINTAVR
	#define TINYAVR_14PIN
#endif

#if (
	defined(__AVR_ATtiny406__)||
	defined(__AVR_ATtiny806__)||
	defined(__AVR_ATtiny1606__)||

	defined(__AVR_ATtiny416__)||
	defined(__AVR_ATtiny816__)||
	defined(__AVR_ATtiny1616__)||
	defined(__AVR_ATtiny3216__)||

	defined(__AVR_ATtiny426__)||
	defined(__AVR_ATtiny826__)||
	defined(__AVR_ATtiny1626__)||
	defined(__AVR_ATtiny3226__)||
)
	#define TINTAVR
	#define TINYAVR_20PIN
#endif

#if (
	defined(__AVR_ATtiny807__)||
	defined(__AVR_ATtiny1607__)||

	defined(__AVR_ATtiny817__)||
	defined(__AVR_ATtiny1617__)||
	defined(__AVR_ATtiny3217__)||

	defined(__AVR_ATtiny427__)||
	defined(__AVR_ATtiny827__)||
	defined(__AVR_ATtiny1627__)||
	defined(__AVR_ATtiny3227__)
)
	#define TINTAVR
	#define TINYAVR_24PIN
#endif

#if (
	defined(__AVR_ATmega808__)|| 
	defined(__AVR_ATmega1608__)||
	defined(__AVR_ATmega3208__)||
	defined(__AVR_ATmega4808__)
)
	#define MEGAAVR
	#define MEGAAVR_32PIN
#endif

#if (
	defined(__AVR_ATmega809__)
	defined(__AVR_ATmega1609__)
	defined(__AVR_ATmega3209__)
	defined(__AVR_ATmega4809__)
)
	#define MEGAAVR
	#define MEGAAVR_48PIN
#endif

#endif
