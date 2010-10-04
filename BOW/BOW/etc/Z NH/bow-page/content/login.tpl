        <div class="box">
            <div class="boxhead">
                <h1>Login</h1>
            </div>

            <div class="boxbody">
		<table>
			<tr><td width="100px"><font size="2px">Username:</font></td><td><input type=text name=user id="login_user" style="background-color:3C80FA;"></td></tr>
			<tr><td width="100px"><font size="2px">Passwort:</font></td><td><input type=password name=pass id="login_pass" style="background-color:3C80FA;"></td></tr>
			
			<tr><td colspan=2 align=left><br><input type=submit value="Login" onclick="runLogin( document.getElementById('login_user').value, document.getElementById('login_pass').value);"></td></tr>
		</table>
            </div>
        </div>