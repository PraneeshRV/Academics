const fs = require('fs');
const fp = __dirname + '/file.txt';
fs.readFile(fp, function(e, d) {
    if(e){
        console.log('err', e);
        return;
    }
    const a = d.toString().split(' ');
    let b = [];
    let x = 0;
    while(x<20){
        b[x]=0;
        x++;
    }
    let y = 0;
    while(y<a.length){
        let z = a[y].toLowerCase();
        if(z!=''){
            let i = 1;
            while(i<=3){
                let s = 0;
                let j = 0;
                while(j<z.length){
                    s = s + z.charCodeAt(j);
                    j++;
                }
                let h = (i + s)%20;
                b[h]=1;
                i++;
            }
        }
        y++;
    }
    console.log(b);
});
