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
  </head>
  <body>
    <div class="container-fluid">
      <h1>Infotron</h1>
      <p>Infotron control page</p>
      </br>
      <h4>Select what to display</h4>
      </br>
      <div class="form-check">
        <label class="form-check-label">
          <input type="radio" class="form-check-input" name="optradio">Date/Time
        </label>
      </div>
      <div class="form-check">
        <label class="form-check-label">
          <input type="radio" class="form-check-input" name="optradio">Weather info
        </label>
      </div>
      <div class="form-check">
        <label class="form-check-label">
          <input type="radio" class="form-check-input" name="optradio">Crypto currency
        </label>
      </div>
      <div class="form-check">
        <label class="form-check-label">
          <input type="radio" class="form-check-input" name="optradio">Text:
        </label>
        <input type="text" id="txt" name="text">
      </div>
      </br>
      <input type="submit" class="btn btn-primary" value="Apply">
    </div>
  </body>
</html>
)=====";
