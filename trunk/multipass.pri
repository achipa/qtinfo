# Do not do this in your projects - we're trained professionals

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
	}
}

