        <div class="box">
            <div class="boxhead">
                <h1>Kontaktformular</h1>
            </div>

            <div class="boxbody">
		<table>
			<tr><td width="100px"><font size="2px">eMail:</font></td><td><input type=text name=from id="contact_from" style="background-color:3C80FA;"></td></tr>
			<tr><td width="100px"><font size="2px">Betreff:</font></td><td><input type=text name=subject id="contact_subject" style="background-color:3C80FA;"></td></tr>
			<tr><td width="100px"><font size="2px">Text:</font></td><td><textarea name=text cols=40 rows=10 id="contact_text" style="background-color:3C80FA;"></textarea></td></tr>
			<tr><td colspan=2 align=center><br><input type=submit value="Abschicken" onclick="runContact( document.getElementById('contact_from').value, document.getElementById('contact_subject').value, document.getElementById('contact_text').value );"></td></tr>
		</table>
            </div>
        </div>