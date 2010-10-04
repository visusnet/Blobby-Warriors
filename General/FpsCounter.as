﻿//===========================================================
//=========================================================//
//						-=ANTHEM=-
//	file: .as
//
//	copyright: Matthew Bush 2007
//
//	notes:
//
//=========================================================//
//===========================================================



//===========================================================
// FPS COUNTER CLASS
//===========================================================
package General{
	
	import flash.display.Sprite;
	import flash.text.*;
	import flash.utils.getTimer;
	import flash.events.*;
	import flash.system.System;
	
	public class FpsCounter extends Sprite{
		
		//======================
		// constructor
		//======================
		public function FpsCounter(){
			
			// create text field
			textBox = new TextField();
			textBox.text = "fps";
			textBox.textColor = 0xffffff;
			textBox.selectable = false;
			
			textBox2 = new TextField();
			textBox2.text = "pfps";
			textBox2.textColor = 0xffffff;
			textBox2.selectable = false;
			textBox2.y = 15;
			
			textBox3 = new TextField();
			textBox3.text = "memory wasted";
			textBox3.textColor = 0xffffff;
			textBox3.selectable = false;
			textBox3.y = 30;
			
			// set initial lastTime
			oldT = getTimer();
			
			addChild(textBox);
			addChild(textBox2);
			addChild(textBox3);
		}
		
		//======================
		// update function
		//======================
		public function update():void{
			var newT:uint = getTimer();
			var f1:uint = newT-oldT;
			mfpsCount += f1;
			if (avgCount < 1){
				textBox.text = "fps:   " + String(Math.round(1000/(mfpsCount/30)));
				avgCount = 30;
				mfpsCount = 0;
			}
			avgCount--;
			oldT = getTimer();
			
			textBox3.text =  "MB:  " + Math.round(System.totalMemory/(1024*1024));
			
		}
		
		
		public function updatePhys(oldT2:uint):void{
			var newT:uint = getTimer();
			var f1:uint = newT-oldT2;
			mfpsCount2 += f1;
			if (avgCount2 < 1){
				textBox2.text = "pfps: " + String(Math.round(1000/(mfpsCount2/30)));
				avgCount2 = 30;
				mfpsCount2 = 0;
			}
			avgCount2--;
		}
		
		
		//======================
		// updateend function
		//======================
		public function updateEnd():void{
			// wrong
			/*var newT:uint = getTimer();
			var f1:uint = newT-oldT;
			mfpsCount2 += f1;
			if (avgCount2 < 1){
				textBox2.text = String(Math.round(1000/(mfpsCount2/30))+" fps uncapped");
				avgCount2 = 30;
				mfpsCount2 = 0;
			}
			avgCount2--;*/
			
		}
		
		
		//======================
		// private variables
		//======================
		private var textBox:TextField;
		private var textBox2:TextField;
		private var textBox3:TextField;
		private var mfpsCount:int = 0;
		private var mfpsCount2:int = 0;
		private var avgCount:int = 30;
		private var avgCount2:int = 30;
		private var oldT:uint;
	}
}




// End of file
//===========================================================
//===========================================================


