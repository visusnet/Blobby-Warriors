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
		public var name:String = "testname.jpg";
		public var image:BitmapData;
		public var x:int;
		public var y:int;
		public var alpha:Number;
		public var rect:Rectangle;

		
		public function toXML():String
		{
			var xml_string:String;
			
			xml_string = "<image posx='" + x + "' posy='" + y + "' src='" + name + "' rotation='" + alpha + "' layer='" + layer + "'></image>";
			
			return xml_string;
		}

		public function BImage(p:BGame, name:String, bitmap:*, xPos:int, yPos:int, alphaRot:Number, layer:Number)
		{
			parent = p;
			
			this.name = name;
			
			image = new BitmapData(bitmap.width, bitmap.height, true, 0x00000000);
			image.draw(bitmap, new Matrix());

			x = xPos;
			y = yPos;
			alpha = alphaRot;
			this.layer = layer;
			rect = new Rectangle(0,0,bitmap.width,bitmap.height);
		}
		
		public function bdraw()
		{
			var tmp_scrollX:int = parent.scrollX;
			var tmp_scrollY:int = parent.scrollY;
			
			if(layer<0)
			{
				tmp_scrollX /= Math.abs(layer);
				tmp_scrollY /= Math.abs(layer);
			}
			else
			{
				
			}
			
			var tmp_layer:int = layer;
			if(tmp_layer==1 || tmp_layer==-1)
			{
				tmp_scrollX = parent.scrollX;
				tmp_scrollY = parent.scrollY;
			}
			
			//trace(tmp_scrollX + " " + tmp_scrollY);
			
			var point:Point=new Point(x - tmp_scrollX, y - tmp_scrollY);
			parent.canvasBD.copyPixels(image, rect, point);
		}
	}
}