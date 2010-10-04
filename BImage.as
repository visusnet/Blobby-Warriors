package 
{
	// Flash
	import flash.events.Event;
	import flash.display.*;
	import flash.text.*;
	import flash.events.*;
	import flash.system.*;
	import flash.ui.*;
	import flash.utils.getTimer;
	import flash.display.MovieClip;
	import flash.net.URLRequest;
	import flash.geom.*;

	// Physic
	import Box2D.Dynamics.*;
	import Box2D.Collision.*;
	import Box2D.Collision.Shapes.*;
	import Box2D.Common.Math.*;
	import Box2D.Dynamics.Joints.*;
	import Box2D.Dynamics.Contacts.*;
	import Box2D.Dynamics.*;
	import Box2D.Common.*;
	import General.*;

	public class BImage
	{
		// ### Atributes ###
		public var parent:BGame;
		
		public var layer:Number;
		public var image:BitmapData;
		public var x:int;
		public var y:int;
		public var alpha:Number;
		public var rect:Rectangle;


		public function BImage(p:BGame, bitmap:*, xPos:int, yPos:int, alphaRot:Number)
		{
			parent = p;
			
			image = new BitmapData(bitmap.width, bitmap.height, true, 0x00000000);
			image.draw(bitmap, new Matrix());

			x = xPos;
			y = yPos;
			alpha = alphaRot;
			layer = 1;
			rect = new Rectangle(0,0,bitmap.width,bitmap.height);
		}
		
		public function bdraw()
		{
			var point:Point=new Point(x - parent.scrollX, y - parent.scrollY);
			parent.canvasBD.copyPixels(image, rect, point);
		}
	}
}