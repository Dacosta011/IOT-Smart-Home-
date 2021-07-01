const url = window.location.href;
console.log(url);
//temperature control
let tempe = document.getElementById("tempe");
// curtains control
let slide = document.getElementById("slide");
let curtain = document.getElementById("cur");
//lights control
let room = document.getElementById("room");
let Living_room = document.getElementById("liv");
let Garage = document.getElementById("gar");
let Dining_room = document.getElementById("din");

slide.addEventListener("change", () => (curtain.innerHTML = slide.value));

room.addEventListener("change", () => {
  fetch(url + "alcoba", {
    method: "POST",
  })
    .then((res) => res.text())
    .then((res) => console.log(res));
});
Living_room.addEventListener("change", () => {
  fetch(url + "sala", {
    method: "POST",
  })
    .then((res) => res.text())
    .then((res) => console.log(res));
});
Garage.addEventListener("change", () => {
  fetch(url + "coche", {
    method: "POST",
  })
    .then((res) => res.text())
    .then((res) => console.log(res));
});
Dining_room.addEventListener("change", () => {
  fetch(url + "comedor", {
    method: "POST",
  })
    .then((res) => res.text())
    .then((res) => console.log(res));
});

slide.addEventListener("change", () => {
  var vall = parseInt(slide.value);
  if (vall == 0 || vall == 180) {
    fetch(url + "cortina", {
      method: "POST",
    })
      .then((res) => res.text())
      .then((res) => console.log(res));
  }
});

window.onload = () => {
  fetch(url + "cortina", {
    method: "POST",
  })
    .then((res) => res.text())
    .then((res) => console.log(res));
};

setInterval(() => {
  fetch(url + "tempe", {
    method: "POST",
  })
    .then((res) => res.text())
    .then((res) => {
      var div = res.split("-");
      tempe.innerHTML = div[1];
      console.log(div[0]);
      if (parseInt(div[0]) < 50) {
        Garage.checked = true;
        Swal.fire({
          title: "Are you at home?",
          text: "Do you want to disable the alarm?",
          icon: "warning",
          showCancelButton: true,
          confirmButtonColor: "#3085d6",
          cancelButtonColor: "#d33",
          confirmButtonText: "Yes, disable it!",
          cancelButtonText: "No",
        }).then((result) => {
          if (result.isConfirmed) {
            fetch(url + "alarma", {
              method: "POST",
            })
              .then((res) => res.text())
              .then((res) => {
                if (res == "ok") {
                  Swal.fire(
                    "Disabled!",
                    "Your alarm has been disabled.",
                    "success"
                  );
                }
              });
          }
        });
        setTimeout(() => {
          fetch(url + "talanquera", {
            method: "POST",
          })
            .then((res) => res.text())
            .then((res) => console.log(res));
        }, 5000);
      }
    });
}, 1000);
