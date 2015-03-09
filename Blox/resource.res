; Writer(s): Kai
; Revision Writer: Dan, Tim, JC, Patrick
;-------------------------------------------------------
; Resource ReadMe and Table of Contents
;-------------------------------------------------------
;
; Format:      [Mark]. [Header] : [Uses]
;
; To locate something within this resource file. Ctrl-F the previous mark.
; For example, to find Texture Background, Ctrl-F and enter T1.
; Add new ones onto the end and add it in the table of contents. Place the mark.
;
; TABLE OF CONTENTS
;
; S1. Sprite bgSpriteEgypt : backgroundEgypt
; S3. Sprite bgSpriteStartScreen : StartScreen
; S4. Sprite bgSpriteAmazon : backgroundAmazon
; S5. Sprite bgSpriteArctic : backgroundArctic
;
; T1. Texture backgroundEgypt : "./Animations/Backgrounds/BackgroundOne.bmp"
; T2. Texture Block : "./Animations/Block.png"
; T3. Texture Goal : "./Animations/TreasureChest.png"
; T4. Texture Statue1 : "./Animations/Egypt/Statue1.png"
; T5. Texture Jars : "./Animations/Egypt/Jars.png"
; T6. Texture WalkUp : "./Animations/walkBack.png"
; T7. Texture WalkLeft : "./Animations/walkLeft.png"
; T8. Texture WalkDown : "./Animations/walkForward.png"
; T9. Texture WalkRight : "./Animations/walkRight.png"
; T10. Texture StartScreen : "./Animations/Backgrounds/Title.bmp"
; T11. Texture Palm : "./Animations/Egypt/Palm.png"
; T12. Texture Statue2 : "./Animations/Egypt/Statue2.png"
; T13. Texture Block1 : filename="./Animations/Egypt/Block1.png"
; T14. Texture Pmid : "./Animations/Egypt/Pmid.png"
; T15. Texture Water : "./Animations/Egypt/Water.bmp"
; T16. Texture Tiger : "./Animations/Amazon/Tiger.png"
; T17. Texture Elephant : ".Animations/Amazon/Elephant.png"
; T18. Texture Plant1 : ".Animations/Amazon/J1.png"
; T19. Texture Plant2 : ".Animations/Amazon/J2.png"
; T20. Texture Tree : ".Animations/Amazon/J3.png"
; T21. Texture Croc : ".Animations/Amazon/Alligator.png"
; T22. Texture backgroundAmazon : ".Animations/Backgrounds/Grass.bmp"
; T33. Texture Plant3 : ".Animations/Amazon/J4.png"
; T34. Texture Jars2 : ".Animations/Amazon/JarsA.png"
; T35. Texture backgroundArctic : "./Animations/Backgrounds/Ice.bmp"
; T36. Texture IceBlock : "./Animations/Arctic/B5.png"
;
; A1. Animation playerUp : WalkUp
; A2. Animation playerDown : WalkDown
; A3. Animation playerRight : WalkRight
; A4. Animation playerLeft : WalkLeft
; A5. Animation statueBlock : Statue1
; A6. Animation waterBlock : Block
; A7. Animation goalBlock : Goal
; A8. Animation transparentBlock : Block
; A9. Animation jarBlock : Jars
; A10. Animation Statue2 : Statue2
; A11. Animation Water : Water
; A12. Animation Palm : Palm
; A13. Animation Block1 : Block1
; A14. Animation Pmid : Pmid
; A15. Animation Tiger : Tiger
; A16. Animation Elephant : Elephant
; A17. Animation Plant1 : Plant1
; A18. Animation Plant2 : Plant2
; A19. Animation Tree : Tree
; A20. Animation Croc : Croc
; A21. Animation Statue3 : Statue3
; A22. Animation Plant3 : Plant3
; A23. Animation Jars2 : Jars2
;
; F1. Font font1 : font1.fnt
;
; M1. Stream theme : music.ogg
;------------------------------------------------------------


Sprite bgSpriteEgypt ;S1.
{
	texture=backgroundEgypt
	rect=0, 0, 640, 640
}
Sprite bgSpriteStartScreen ;S3
{
	texture=StartScreen
	rect=0,0,800,600
}
Sprite bgSpriteAmazon ;S4
{
	texture=backgroundAmazon
	rect=0,0,640,640
}
Sprite bgSpriteArctic ;S5
{
	texture=backgroundArctic
	rect=0,0,640,640
}
Sprite bgSpriteCredits ;S6
{
	texture=Credits
	rect=0,0,1024,768
}
Sprite Tutorial ;S21
{
	texture=Tutorial
	rect=0,0,800,600
}
Sprite Options ;S22
{
	texture=Options
	rect=0,0,800,600
}
Sprite Game ;S23
{
	texture=Game
	rect=0,0,800,600
}
Sprite Code ;S24
{
	texture=Code
	rect=0,0,800,600
}
Sprite End_Game ;S25
{
	texture=End_Game
	rect=0,0,800,600
}
Sprite interfaceSprite1 ;26
{
	texture=interface1
	rect=0,0,512,512
}
Sprite bgSpriteTutorial ; S6
{
	texture=backgroundTutorial
	rect=0,0,640,640
}
Texture backgroundEgypt ;T1.
{
 filename="./Animations/Backgrounds/BackgroundOne.bmp"
}
Texture Block ;T2.
{
	filename="./Animations/Block.png"
}
Texture Goal ;T3.
{
	filename="./Animations/TreasureChest.png"
}
Texture Statue1 ;T4.
{
	filename="./Animations/Egypt/Statue1.png"
}
Texture Jars ;T5.
{
	filename="./Animations/Egypt/Jars.png"
}
Texture WalkUp ;T6.
{
	filename="./Animations/walkBack.png"
}
Texture WalkLeft ;T7.
{
	filename="./Animations/walkLeft.png"
}
Texture WalkDown ;T8.
{
	filename="./Animations/walkForward.png"
}
Texture WalkRight ;T9.
{
	filename="./Animations/walkRight.png"
}
Texture StartScreen ;T10.
{
	filename="./Animations/Backgrounds/Title.bmp"
}
Texture Palm ;T11
{
	filename="./Animations/Egypt/Palm.png"
}
Texture Statue2 ;T12
{
	filename="./Animations/Egypt/Statue2.png"
}
Texture Block1 ;T13
{
	filename="./Animations/B1.png"
}
Texture Pmid ;T14
{
	filename="./Animations/Egypt/Pmid.png"
}
Texture Water ;T15
{
	filename="./Animations/Egypt/Water.bmp"
}
Texture Tiger ; T16. 
{
	filename= "./Animations/Amazon/Tiger.png"
}
Texture Elephant ; T17.
{
	filename="./Animations/Amazon/Elephant.png"
}
Texture Plant1 ; T18.
{
	filename="./Animations/Amazon/J1.png"
}
Texture Plant2 ; T19.
{
	filename="./Animations/Amazon/J2.png"
}
Texture Tree ; T20.
{
	filename="./Animations/Amazon/J3.png"
}
Texture Croc ; T21.
{
	filename="./Animations/Amazon/Alligator.png"
}
Texture backgroundAmazon ; T22.
{
	filename="./Animations/Backgrounds/Level1Map3.bmp"
}
Texture Statue3 ; T23.
{
	filename="./Animations/Egypt/Statue3.png"
}
Texture Plant3
{
	filename="./Animations/Amazon/J4.png"
}
Texture Jars2 ; T34. 
{
	filename="./Animations/Amazon/JarsA.png"
}
Texture backgroundArctic ;T35
{
	filename="./Animations/Backgrounds/Ice.bmp"
}
Texture IceBlock
{
	filename="./Animations/Ice/B5.png"
}
Texture Background2 
{
	filename=title_II.bmp
}
Texture Tutorial
{
	filename=tutorial_proto.bmp
}
Texture Options
{
	filename=options_proto.bmp
}
Texture Game
{
	filename=game_proto.bmp
}
Texture Code
{
	filename=code_proto.bmp
}
Texture End_Game
{
	filename=end_game.bmp
}
Texture interface1 
{
 filename="./Animations/interface1.bmp"
}
Texture backgroundTutorial ;T36
{
	filename="./Animations/Backgrounds/TutorialBG.PNG"
}
Texture Penguin ;T37
{
	filename="./Animations/Ice/Penguin.PNG"
}
Texture PolarBear ;T38
{
	filename="./Animations/Ice/PolarBear.PNG"
}
Texture Credits ;T38
{
	filename="./Animations/Backgrounds/Background.PNG"
}
Animation playerUp ;A1.
{
	texture=WalkUp
	rect=0,0,32,32
	frames=4
	fps=5.0
	mode=FORWARD,LOOP
}
Animation playerDown ;A2.
{
	texture=WalkDown
	rect=0,0,32,32
	frames=4
	fps=5.0
	mode=FORWARD,LOOP
}
Animation playerRight ;A3.
{
	texture=WalkRight
	rect=0,0,32,32
	frames=4
	fps=5.0
	mode=FORWARD,LOOP
}
Animation playerLeft ;A4.
{
	texture=WalkLeft
	rect=0,0,32,32
	frames=4
	fps=5.0
	mode=FORWARD,LOOP
}
Animation statueBlock ;A5.
{
 texture=Statue1
 rect=0, 0, 32, 32
 frames=5
 fps=0.1
 mode=FORWARD,LOOP
}
Animation waterBlock ;A6.
{
 texture=Block
 rect=32, 0, 32, 32
 frames=5
 fps=0.1
 mode=FORWARD,LOOP
}
Animation goalBlock ;A7.
{
 texture=Goal
 rect=0, 0, 32, 32
 frames=1
 fps=0.1
 mode=FORWARD,LOOP
}
Animation transparentBlock ;A8.
{
 texture=Block
 rect=128, 0, 32, 32
 frames=5
 fps=0.1
 mode=FORWARD,LOOP
}

Animation jarBlock ;A9.
{
 texture=Jars
 rect=0, 0, 32, 32
 frames=1
 fps=0.1
 mode=FORWARD,LOOP
}
Animation Statue2 ;A10
{
 texture=Statue2
 rect=0, 0, 32, 32
 frames=5
 fps=0.1
 mode=FORWARD,LOOP
}
Animation Water ;A11
{
 texture=Water
 rect=0, 0, 32, 32
 frames=5
 fps=0.1
 mode=FORWARD,LOOP
}
Animation Palm ;A12
{
 texture=Palm 
 rect=0, 0, 32, 32
 frames=5
 fps=0.1
 mode=FORWARD,LOOP
}
Animation Block1 ;A13
{
 texture=Block1
 rect=0, 0, 32, 32
 frames=1
 fps=0.1
 mode=FORWARD,LOOP
}
Animation Pmid ;A14
{
 texture=Pmid
 rect=0, 0, 32, 32
 frames=1
 fps=0.1
 mode=FORWARD,LOOP
}
Animation Tiger ; A15.
{
 texture=Tiger
 rect=0, 0, 32, 32
 frames=1
 fps=0.1
 mode=FORWARD,LOOP
}
Animation Elephant ; A16.
{
 texture=Elephant
 rect=0, 0, 32, 32
 frames=1
 fps=0.1
 mode=FORWARD,LOOP
}
Animation Plant1 ; A17. 
{
 texture=Plant1
 rect=0, 0, 32, 32
 frames=1
 fps=0.1
 mode=FORWARD,LOOP
}
Animation Plant2 ; A18.  
{
 texture=Plant2
 rect=0, 0, 32, 32
 frames=1
 fps=0.1
 mode=FORWARD,LOOP
}
Animation Tree ; A19. 
{
 texture=Tree
 rect=0, 0, 32, 32
 frames=1
 fps=0.1
 mode=FORWARD,LOOP
}
Animation Croc ; A20. 
{
 texture=Croc
 rect=0, 0, 32, 32
 frames=1
 fps=0.1
 mode=FORWARD,LOOP
}
Animation Statue3 ; A21.
{
 texture=Statue3
 rect=0, 0, 32, 32
 frames=5
 fps=0.1
 mode=FORWARD,LOOP
}
Animation Plant3 ; A22.
{
	texture=Plant3
	rect=0, 0, 32, 32
	frames=5
	fps=0.1
	mode=FORWARD,LOOP
}
Animation Jars2 ; A23.
{
	texture=Jars2
	rect=0, 0, 32, 32
	frames=1
	fps=0.1
	mode=FORWARD,LOOP
}
Animation iceBlock ;A24.
{
	texture=IceBlock
	rect=0, 0, 32, 32
	frames=1
	fps=0.1
	mode=FORWARD,LOOP
}
Animation Marble ; A25
{
 texture=Block
 rect=96, 0, 32, 32
 frames=5
 fps=2.0
 mode=FORWARD,LOOP
}
Animation Wall ; A26
{
 texture=Block
 rect=128, 0, 32, 32
 frames=5
 fps=2.0
 mode=FORWARD,LOOP
}

Animation Dragon ; A27
{
 texture=Block
 rect=160, 0, 32, 32
 frames=5
 fps=2.0
 mode=FORWARD,LOOP
}
Animation PolarBear ; A27
{
 texture=PolarBear
 rect=0, 0, 32, 32
 frames=1
 fps=2.0
 mode=FORWARD,LOOP
}
Animation Penguin ; A27
{
 texture=Penguin
 rect=0, 0, 32, 32
 frames=1
 fps=2.0
 mode=FORWARD,LOOP
}
Font font1 ;F1.
{
 filename=font1.fnt
}
Font font
{
filename=font.fnt
}

Stream themeEGYPT ;M1.
{
	filename=musicEGYPT.ogg
}
Stream themeAMAZON ;M1.
{
	filename=song3.ogg
}
Stream endGame
{
	filename=Balun-snol.ogg
}
