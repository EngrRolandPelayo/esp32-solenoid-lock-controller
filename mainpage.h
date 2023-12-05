/*
 * This file contains HTML script for the home page
*/
const String page PROGMEM = R"(
    <html>
    <head>
        <meta name='viewport' content='width=device-width, initial-scale=1.0'>         
        <style>

            body {
              font-family: Roboto;  
            }
            
            #header {
              text-align: center;
            }

            #content {
              text-align: center;
            }

            .spacer {
              height: 5%;
            }
            
            #switch {
              position: relative;
              display: inline-block;
              left: 100%;
              bottom: 15%;
              font-weight: 500;
            }
            
            .switch {
              position: relative;
              display: inline-block;
              width: 60px;
              height: 34px;
              left: -30px;
            }
            
            .switch input { 
              opacity: 0;
              width: 0;
              height: 0;
            }
            
            .slider {
              position: absolute;
              cursor: pointer;
              top: 0;
              left: 0;
              right: 0;
              bottom: 0;
              background-color: #ccc;
              -webkit-transition: .4s;
              transition: .4s;
            }
            
            .slider:before {
              position: absolute;
              content: "";
              height: 26px;
              width: 26px;
              left: 4px;
              bottom: 4px;
              background-color: white;
              -webkit-transition: .4s;
              transition: .4s;
            }
            
            input:checked + .slider {
              background-color: #2196F3;
            }
            
            input:focus + .slider {
              box-shadow: 0 0 1px #2196F3;
            }
            
            input:checked + .slider:before {
              -webkit-transform: translateX(26px);
              -ms-transform: translateX(26px);
              transform: translateX(26px);
            }
            
            /* Rounded sliders */
            .slider.round {
              border-radius: 34px;
            }
            
            .slider.round:before {
              border-radius: 50%;
            }
        </style>
    
    </head>
    <body>
        <div id='header'>
            <h1>ESP32 Solenoid Controller</h1>
        </div>
        <div class='spacer'></div>
        <div id='content'>
            <form>
                <label class='switch'> 
                  <input type='checkbox' id='myCheckbox' name='myCheckbox'>
                  <span class='slider round'></span>
                  <p id='switch'>OFF</p>
                </label>
            </form>

            <script>
                var checkbox = document.getElementById('myCheckbox');
        
                // Attach a change event listener to the checkbox
                checkbox.addEventListener('change', function() {
                  var state = checkbox.checked;
                  if(state == true){
                    document.getElementById('switch').innerHTML = 'ON';
                  }else{
                    document.getElementById('switch').innerHTML = 'OFF';
                  }
                  var xhr = new XMLHttpRequest();
                  xhr.open('GET', '/switchState?state=' + state,true);
                  xhr.send();
                });
            </script>
        </div>
        <div class='spacer'></div>
        <div id='footer'>
            <p>source: <a href='https://www.teachmemicro.com'>teachmemicro.com</a></p>
        </div>
    </body>
</html>
 )";
