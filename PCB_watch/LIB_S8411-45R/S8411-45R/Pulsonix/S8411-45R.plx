PULSONIX_LIBRARY_ASCII "SamacSys ECAD Model"
//686647/1046898/2.49/2/4/Undefined or Miscellaneous

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r450_230"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 2.3) (shapeHeight 4.5))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(padStyleDef "c130_h130"
		(holeDiam 1.3)
		(padShape (layerNumRef 1) (padShapeType Ellipse)  (shapeWidth 1.3) (shapeHeight 1.3))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 1.3) (shapeHeight 1.3))
	)
	(padStyleDef "c105_h105"
		(holeDiam 1.05)
		(padShape (layerNumRef 1) (padShapeType Ellipse)  (shapeWidth 1.05) (shapeHeight 1.05))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 1.05) (shapeHeight 1.05))
	)
	(textStyleDef "Normal"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 1.27)
			(strokeWidth 0.127)
		)
	)
	(patternDef "S8411-45R_1" (originalName "S8411-45R_1")
		(multiLayer
			(pad (padNum 1) (padStyleRef r450_230) (pt 0, -8.2) (rotation 0))
			(pad (padNum 2) (padStyleRef c130_h130) (pt 0, 8.2) (rotation 90))
			(pad (padNum 3) (padStyleRef c105_h105) (pt 0, 3.725) (rotation 90))
			(pad (padNum 4) (padStyleRef r450_230) (pt 0, 8.2) (rotation 0))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt -0.412, 0.096) (textStyleRef "Normal") (isVisible True))
		)
		(layerContents (layerNumRef 28)
			(arc (pt 0, 0) (radius 0) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -6.832 -8.307) (pt 6.832 -8.307) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(line (pt -6.832 -8.307) (pt -6.832 -6.625) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 6.832 -8.307) (pt 6.832 -6.625) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(line (pt -6.832 -6.625) (pt -3.27 -6.625) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 6.832 -6.625) (pt 3.27 -6.625) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(arc (pt 0, 0) (radius 7.4) (startAngle 116.5) (sweepAngle 127.1) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(arc (pt -4.9999999998107E-6, 0) (radius 7.400005) (startAngle 296.5) (sweepAngle 127.1) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -3.29687 -6.625) (pt -6.832 -6.625) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -6.832 -6.625) (pt -6.832 -8.307) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(line (pt 6.832 -8.307) (pt 6.832 -6.625) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt 6.832 -6.625) (pt 3.296 -6.625) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -6.832 -8.307) (pt -1.553 -8.307) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt 6.832 -8.307) (pt 1.49 -8.307) (width 0.1))
		)
	)
	(symbolDef "S8411-45R" (originalName "S8411-45R")

		(pin (pinNum 1) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 2) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(line (pt 200 mils 100 mils) (pt 600 mils 100 mils) (width 6 mils))
		(line (pt 600 mils 100 mils) (pt 600 mils -200 mils) (width 6 mils))
		(line (pt 600 mils -200 mils) (pt 200 mils -200 mils) (width 6 mils))
		(line (pt 200 mils -200 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 650 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))
		(attr "Type" "Type" (pt 650 mils 200 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))

	)
	(compDef "S8411-45R" (originalName "S8411-45R") (compHeader (numPins 2) (numParts 1) (refDesPrefix U)
		)
		(compPin "1" (pinName "+") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "2" (pinName "-") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Unknown))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "S8411-45R"))
		(attachedPattern (patternNum 1) (patternName "S8411-45R_1")
			(numPads 2)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
			)
		)
		(attr "Mouser Part Number" "855-S8411-45R")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/Harwin/S8411-45R?qs=Qom7kyPojXY6B0JhnWxDgQ%3D%3D")
		(attr "Manufacturer_Name" "Harwin")
		(attr "Manufacturer_Part_Number" "S8411-45R")
		(attr "Description" "HARWIN - S8411-45R - HOLDER, COIN CELL, CR1220, FULL REEL")
		(attr "<Hyperlink>" "https://cdn.harwin.com/pdfs/S8411R.pdf")
		(attr "<STEP Filename>" "S8411-45R.stp")
		(attr "<STEP Offsets>" "X=0;Y=0.7;Z=0.23")
		(attr "<STEP Rotation>" "X=90;Y=0;Z=0")
	)

)
