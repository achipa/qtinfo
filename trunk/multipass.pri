# Do not do this in your projects - we're trained professionals

symbian:TARGET.UID3=0xA1234567


PASS=1



contains(PASS,1) {
	maemo5 {
		MOBCONFIG=mobility12
		MOBLOAD=mobilityconfig12
	}
}

contains(PASS,2) {
	maemo5 {
		MOBCONFIG=mobility11
		MOBLOAD=mobilityconfig11
	}
}

contains(PASS,3) {
	maemo5 {
		MOBCONFIG=mobility
#		MOBLOAD=mobilityconfig10 # mobility 1.0 has no config
	}
}

