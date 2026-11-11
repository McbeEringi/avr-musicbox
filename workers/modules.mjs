const
config_default={
	title:'avr-musicbox',
	desc:'A simple yet powerful musicbox built on tinyAVR0',
	origin:'https://avr-musicbox.6ca.me/'
},
html_tmpl=c=>x=>({...x,html:`\
<!DOCTYPE html>
<html prefix="og:http://ogp.me/ns#" lang="ja"><head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width,initial-scale=1">
	<title>${c.title}</title>
	<meta name="description" content="${c.desc}">
	<link rel="icon" type="image/png" href="/img/favicon.png">
	<link rel="icon" type="image/svg+xml" href="/img/favicon.svg">
	<link rel="apple-touch-icon" href="/img/apple-touch-icon.png">
	<meta property="og:type" content="website">
	<meta property="og:title" content="${c.title}">
	<meta property="og:description" content="${c.desc}">
	<meta property="og:url" content="${new URL(x.path,c.origin)}">
	<meta property="og:image" content="${new URL('/img/apple-touch-icon.png',c.origin)}">
	<link href="https://6ca.me/src/style.css" rel="stylesheet">
${x.style.length?`\t<style>${x.style.join('\n')}\t</style>\n`:''}\
	<script>document.documentElement.addEventListener('touchstart',_=>_,{passive:true});</script>
</head><body>
${x.html}\
</body></html>
`});
export{config_default,html_tmpl};
