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
		public var width:int;
		public var height:int;
		public var alpha:Number;
		public var rect:Rectangle;
		public var loader:Loader;
		public var images:Array;
		public var images_positions:Array;
		public var loadComplete:Boolean = false;
		
		

		
		public function toXML():String
		{
			var xml_string:String;
			
			xml_string = "<image posx='" + x + "' posy='" + y + "' src='" + name + "' rotation='" + alpha + "' layer='" + layer + "'></image>";
			
			return xml_string;
		}

		public function BImage(p:BGame, name:String, xPos:int, yPos:int, alphaRot:Number, layer:Number)
		{
			parent = p;
			
			this.name = name;
			
			x = xPos;
			y = yPos;
			alpha = alphaRot;
			this.layer = layer;
			rect = new Rectangle(0,0,0,0);
			
			images = new Array();
			images_positions = new Array();
		}
		
		public function progressHandler(event:ProgressEvent)
		{
			trace("progressHandler: bytesLoaded=" + event.bytesLoaded + " bytesTotal=" + event.bytesTotal);
		}

		public function onImageLoadError(event:Event):void
		{
			trace("errorrr");
		}
			
		
		public function onImageLoadComplete(event:Event):void
		{
			trace("fertig");

			// set dimensions
			this.width = loader.contentLoaderInfo.width;
			this.height = loader.contentLoaderInfo.height;
			rect = new Rectangle(0,0,width,height);
			
			
			// split into many smaller Bitmaps
			var tmp_splitRate:int = 2880;
			
			var tmp_point:Point = new Point();
			tmp_point.x = 0;
			tmp_point.y = 0;

			while(tmp_point.y < height)
			{
				var height_count:int;
				
				if(height-tmp_point.y > tmp_splitRate)
				{
					height_count = tmp_splitRate;
				}
				else
				{
					height_count = height-tmp_point.y;
				}
					
				while(tmp_point.x < width)
				{
					var width_count:int;
					
					if(width-tmp_point.x > tmp_splitRate)
					{
						width_count = tmp_splitRate;
					}
					else
					{
						width_count = width-tmp_point.x;
					}
					
					// neues Bitmap erstellen
					var tmp_bmp:BitmapData = new BitmapData(width_count, height_count, true, 0x00000000);
					var tmp_bmp_treshold:BitmapData = new BitmapData(width_count, height_count, true, 0x00000000);
					
					var translateMatrix:Matrix = new Matrix();
					translateMatrix.translate(-tmp_point.x, -tmp_point.y);
			
					tmp_bmp.draw(loader, translateMatrix);
					
					// Transparent Color
					var threshold:uint =  0x00FFFF00; 
					var color:uint = 0x00000000;
					var maskColor:uint = 0x00FF0000;
					
					tmp_bmp_treshold.threshold(tmp_bmp, new Rectangle(0, 0, width_count, height_count) , new Point(0, 0), ">=", threshold, color, maskColor, true);

					
					
					images.push(tmp_bmp_treshold);
					images_positions.push(new Point(tmp_point.x,tmp_point.y));
					
					tmp_point.x += width_count;
				}
				
				tmp_point.y += height_count;
				tmp_point.x = 0;
			}
			
			parent.level.images.push(this);
			
			
			loadComplete = true;
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
			
			// Scrolling-Position
			var point:Point=new Point(x-parent.scrollX, y-parent.scrollY);

			// draw - better copyPixels? problem: BitAssCanvas
			var img:BitmapData;
			for (var i:int = 0; i < images.length; i++)
			{
				img = images[i];
				var img_point:Point = images_positions[i] as Point;
				
				// Matrix
				var translateMatrix:Matrix = new Matrix();
				translateMatrix.translate(point.x + img_point.x, point.y + img_point.y);
			
				parent.canvasBD.draw(img, translateMatrix, null, null, new Rectangle(point.x + img_point.x,point.y + img_point.y,img.width,img.height), null);
			}
		}
	}
}