const char WEB_PAGE[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Infotron</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.0/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.0/umd/popper.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.0/js/bootstrap.min.js"></script>
    <script>function SendData(){
      strLine = "";
      if (document.getElementById("optTime").checked) strLine = "time=1";
      if (document.getElementById("optWeather").checked) strLine =  "weather=1";
      if (document.getElementById("optCrypto").checked) strLine = "crypto=1";
      if (document.getElementById("optText").checked) strLine = "text=" + document.getElementById("txt").value;
      $.post("infotron?" + strLine);
      document.getElementById("apply").blur();
      }
    </script>
  </head>
  <body>
    <div class="container-fluid">
      <h1>Infotron</h1>
      <p>Infotron control page</p>
      </br>
      <h4>Select what to display</h4>
      </br>
      <div class="form-check">
        <input type="radio" id="optTime" class="form-check-input" name="optradio" disabled>
        <label class="form-check-label">Date/Time</label>
      </div>
      <div class="form-check">
        <input type="radio" id="optWeather" class="form-check-input" name="optradio" disabled>
        <label class="form-check-label">Weather info</label>
      </div>
      <div class="form-check">
        <input type="radio" id="optCrypto" class="form-check-input" name="optradio" disabled>
        <label class="form-check-label">Crypto currency rates</label>
      </div>
      <div class="form-check">
        <input type="radio" id="optText" class="form-check-input" name="optradio" checked="true">
        <label class="form-check-label">Text:</label>
        <input type="text" id="txt" name="text" autofocus>
      </div>
      </br>
      <input type="submit" id="apply" class="btn btn-primary" onclick="SendData()" value="Apply">
    </div>
  </body>
</html>
)=====";
