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
	
	
	public class BKey
	{
		public var pressed:Boolean;
		public var time_pressedTotal:uint;
		private var time_down:uint;
		private var time_up:uint;
		private var time_step_down:uint;
		private var old_state:Boolean;
		
		public function BKey()
		{
			pressed = false;
			old_state = pressed;
		}
		
		public function isPressed()
		{
			time_pressedTotal = getTimer() - time_down;
			
			if((getTimer() - time_step_down) > 100 || time_down == 0)
			{
				time_step_down = getTimer();
				return pressed;
			}
			else
				return false;
		}
		
		public function hasChanged()
		{
			var tmp_old_state:Boolean = old_state;
			old_state = pressed;
			
			if(tmp_old_state != pressed)
				return true;
			else
				return false;
		}
		
		public function down()
		{
			if(pressed == false)
			{
				time_down = getTimer();
				time_step_down = 0;
				time_pressedTotal = 0;
				pressed = true;
			}
		}
		
		public function up()
		{
			time_up = getTimer();
			pressed = false;
		}
	}
}